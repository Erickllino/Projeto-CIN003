import cv2
import mediapipe as mp
import serial #Biblioteca para comunicação serial (pyserial)
import time


porta = '/dev/ttyACM0'
def connect_to_arduino(port='COM6', baud_rate=9600, timeout=2, attempts=5):
    for attempt in range(attempts):
        try:
            print(f"Attempting to connect to Arduino on {port} (attempt {attempt+1}/{attempts})")
            ser = serial.Serial(port, baud_rate, timeout=timeout)
            time.sleep(2)  
            print("Successfully connected to Arduino")
            return ser
        except serial.SerialException as e:
            print(f"Failed to connect: {e}")
            if attempt < attempts - 1:
                print("Retrying in 3 seconds...")
                time.sleep(3)
    
    print("Could not establish connection to Arduino. Please check your connections.")
    return None

# Conecta ao Arduino
ser = connect_to_arduino()
if ser is None:
    print("Exiting program due to connection failure")
    exit()

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
        return 'P'
    elif not indicador and not medio and not anelar and not mindinho:
        return 'R'
    elif indicador and medio and not anelar and not mindinho:
        return 'S'
    else:
        return "Desconhecido"

def enviar_sinal(gesto):
    # Envia o gesto para o Arduino via serial
    if gesto in ['R', 'P', 'S']:
        
        ser.write(gesto.encode())  # Envia o gesto como string para o Arduino
        print(f"Enviado para o Arduino: {gesto}")


  # Exibe os dados recebidos

    #time.sleep(1)  # Pequeno delay para evitar sinais rápidos demais

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
