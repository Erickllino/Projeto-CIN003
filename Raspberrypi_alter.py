import cv2
import numpy as np
import RPi.GPIO as GPIO
import time

# Configuração dos pinos GPIO
GPIO.setmode(GPIO.BCM)
GPIO_PEDRA = 17   # Ajuste conforme necessário
GPIO_PAPEL = 27   # Ajuste conforme necessário
GPIO_TESOURA = 22 # Ajuste conforme necessário

GPIO.setup(GPIO_PEDRA, GPIO.OUT)
GPIO.setup(GPIO_PAPEL, GPIO.OUT)
GPIO.setup(GPIO_TESOURA, GPIO.OUT)

# Inicialização da câmera (com resolução reduzida para melhor desempenho no RPi 3)
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

# Parâmetros para detecção de pele
lower_skin = np.array([0, 20, 70], dtype=np.uint8)
upper_skin = np.array([20, 255, 255], dtype=np.uint8)

# Variáveis de estado
ultimo_gesto = "Desconhecido"
contador_estabilidade = 0
min_estabilidade = 5  # Número de frames consistentes para confirmar gesto

def detectar_gesto(contorno, frame):
    # Criar uma cópia do frame para desenhar
    drawing = frame.copy()
    
    # Encontrar o contorno da mão (maior contorno)
    if len(contorno) > 0:
        max_contorno = max(contorno, key=cv2.contourArea)
        
        # Verificar se o contorno é grande o suficiente para ser uma mão
        if cv2.contourArea(max_contorno) < 3000:
            return "Desconhecido", drawing
            
        # Encontrar o contorno convexo (convex hull)
        hull = cv2.convexHull(max_contorno)
        
        # Desenhar o contorno e o hull
        cv2.drawContours(drawing, [max_contorno], 0, (0, 255, 0), 2)
        cv2.drawContours(drawing, [hull], 0, (0, 0, 255), 2)
        
        # Encontrar defeitos de convexidade
        hull = cv2.convexHull(max_contorno, returnPoints=False)
        defects = cv2.convexityDefects(max_contorno, hull)
        
        # Contar dedos
        dedos = 0
        
        if defects is not None:
            for i in range(defects.shape[0]):
                s, e, f, d = defects[i, 0]
                start = tuple(max_contorno[s][0])
                end = tuple(max_contorno[e][0])
                far = tuple(max_contorno[f][0])
                
                # Calcular a distância entre pontos
                a = np.sqrt((end[0] - start[0]) ** 2 + (end[1] - start[1]) ** 2)
                b = np.sqrt((far[0] - start[0]) ** 2 + (far[1] - start[1]) ** 2)
                c = np.sqrt((end[0] - far[0]) ** 2 + (end[1] - far[1]) ** 2)
                
                # Calcular o ângulo
                angle = np.arccos((b ** 2 + c ** 2 - a ** 2) / (2 * b * c))
                
                # Se o ângulo for menor que 90 graus, é provavelmente um dedo
                if angle <= np.pi / 2:
                    dedos += 1
                    # Desenhar um círculo no ponto de defeito
                    cv2.circle(drawing, far, 5, [0, 0, 255], -1)
            
            # Ajustar contagem de dedos (o algoritmo conta vales, não dedos)
            dedos += 1
            
            # Determinar o gesto com base na contagem de dedos
            if dedos <= 1:
                return "Pedra", drawing
            elif dedos >= 5:
                return "Papel", drawing
            elif dedos >= 3:
                return "Tesoura", drawing
            else:
                return "Desconhecido", drawing
        else:
            return "Desconhecido", drawing
    
    return "Desconhecido", drawing

def enviar_sinal(gesto):
    GPIO.output(GPIO_PEDRA, GPIO.LOW)
    GPIO.output(GPIO_PAPEL, GPIO.LOW)
    GPIO.output(GPIO_TESOURA, GPIO.LOW)
    
    if gesto == "Pedra":
        GPIO.output(GPIO_PEDRA, GPIO.HIGH)
    elif gesto == "Papel":
        GPIO.output(GPIO_PAPEL, GPIO.HIGH)
    elif gesto == "Tesoura":
        GPIO.output(GPIO_TESOURA, GPIO.HIGH)

try:
    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break
            
        # Redimensionar para processamento mais rápido
        frame = cv2.resize(frame, (320, 240))
        
        # Converter para HSV para melhor detecção de pele
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        
        # Criar máscara para detectar a cor da pele
        mask = cv2.inRange(hsv, lower_skin, upper_skin)
        
        # Operações morfológicas para melhorar a detecção
        kernel = np.ones((5, 5), np.uint8)
        mask = cv2.dilate(mask, kernel, iterations=2)
        mask = cv2.erode(mask, kernel, iterations=1)
        
        # Aplicar blur para suavizar a imagem
        mask = cv2.GaussianBlur(mask, (5, 5), 100)
        
        # Encontrar contornos
        contornos, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        
        # Detectar gesto
        gesto, drawing = detectar_gesto(contornos, frame)
        
        # Estabilizar a detecção (evitar mudanças rápidas)
        if gesto == ultimo_gesto:
            contador_estabilidade += 1
        else:
            contador_estabilidade = 0
            ultimo_gesto = gesto
        
        # Só enviar sinal se o gesto for estável por alguns frames
        if contador_estabilidade >= min_estabilidade and gesto != "Desconhecido":
            enviar_sinal(gesto)
            # Mostrar o gesto detectado na tela
            cv2.putText(drawing, gesto, (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
        else:
            cv2.putText(drawing, "Analisando...", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
        
        # Exibir a máscara e o resultado
        cv2.imshow("Mascara", mask)
        cv2.imshow("Resultado", drawing)
        
        # Sair com a tecla 'q'
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

finally:
    cap.release()
    cv2.destroyAllWindows()
    GPIO.cleanup()  # Descomentei para limpar os pinos GPIO ao encerrar