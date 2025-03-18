import cv2
import mediapipe as mp
import serial
import time

# Configuração da comunicação serial com o Arduino
ser = serial.Serial('COM3', 9600)  # Altere 'COM3' para a porta serial correta no seu sistema
time.sleep(2)  # Aguarda 2 segundos para garantir que a comunicação serial esteja estável

mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils
hands = mp_hands.Hands()

cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1024)

def distance(lm, a, b):
    return (lm[a].x - lm[b].x) ** 2 + (lm[a].y - lm[b].y) ** 2 + (lm[a].z - lm[b].z) ** 2

def detectar_gesto(hand_landmarks):
    lm = hand_landmarks.landmark
    
    x = (lm[5].x + lm[9].x + lm[13].x + lm[17].x) / 4
    y = (lm[5].y + lm[9].y + lm[13].y + lm[17].y) / 4
    z = (lm[5].z + lm[9].z + lm[13].z + lm[17].z) / 4
    d = (lm[0].y - y) ** 2 + (lm[0].x - x) ** 2 + (lm[0].z - z) ** 2

    d1 = distance(lm, 8, 0) / d
    d2 = distance(lm, 12, 0) / d
    d3 = distance(lm, 16, 0) / d
    d4 = distance(lm, 20, 0) / d
    
    threshold = 1
    indicador = d1 > threshold
    medio = d2 > threshold
    anelar = d3 > threshold
    mindinho = d4 > threshold

    if indicador and medio and anelar and mindinho:
        return "Papel"
    elif not indicador and not medio and not anelar and not mindinho:
        return "Pedra"
    elif indicador and medio and not anelar and not mindinho:
        return "Tesoura"
    else:
        return "Desconhecido"

def enviar_sinal(gesto):
    # Envia o gesto para o Arduino via serial
    if gesto in ["Pedra", "Papel", "Tesoura"]:
        ser.write(gesto.encode())  # Envia o gesto como string para o Arduino
        print(f"Enviado para o Arduino: {gesto}")
    time.sleep(1)  # Pequeno delay para evitar sinais rápidos demais

try:
    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break

        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        results = hands.process(frame)
        frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

        if results.multi_hand_landmarks:
            for hand_landmarks in results.multi_hand_landmarks:
                gesto = detectar_gesto(hand_landmarks)
                print(gesto)
                enviar_sinal(gesto)
                mp_drawing.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)

        cv2.imshow("Hand Tracking", frame)
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break
finally:
    cap.release()
    cv2.destroyAllWindows()
    ser.close()  # Fecha a conexão serial com o Arduino
