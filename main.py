import cv2
import mediapipe as mp

mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils
hands = mp_hands.Hands()

cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1024)

def detectar_gesto(hand_landmarks):
    # Extraindo os pontos de interesse
    lm = hand_landmarks.landmark

    # Verifica se os dedos estão estendidos (ignora o polegar para essa lógica)
    
    
    x = (lm[5].x + lm[9].x + lm[13].x + lm[17].x)/4
    y = (lm[5].y + lm[9].y + lm[13].y + lm[17].y)/4
    z = (lm[5].z + lm[9].z + lm[13].z + lm[17].z)/4
    d = (lm[0].y - y)**2 + (lm[0].x - x)**2 + (lm[0].z - z)**2
   
    d1 = distance(lm,8,0)/d
    d2 = distance(lm,12,0)/d
    d3 = distance(lm,16,0)/d
    d4 = distance(lm,20,0)/d
        
    print(f'd1: {d1}, d2: {d2}, d3: {d3}, d4: {d4}')
    
    # Limiar para considerar o dedo estendido
    threshold = 1

    indicador = d1 > threshold
    medio = d2 > threshold
    anelar = d3 > threshold
    mindinho = d4 > threshold

    # Regra para cada gesto:
    if indicador and medio and anelar and mindinho:
        return "Papel"
    elif not indicador and not medio and not anelar and not mindinho:
        return "Pedra"
    elif indicador and medio and not anelar and not mindinho:
        return "Tesoura"
    else:
        return "Desconhecido"

def distance(lm,a,b):
    return (lm[a].x - lm[b].x)**2 + (lm[a].y - lm[b].y)**2 + (lm[a].z - lm[b].z)**2

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = hands.process(frame)
    frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
    
    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            print(detectar_gesto(hand_landmarks))

            mp_drawing.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)
    
    cv2.imshow("Hand Tracking", frame)
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
