import base64
from PIL import Image
from io import BytesIO
import requests

def decode_base64_and_show_image(file_path):
    # Lee el archivo de texto con datos en base64
    with open(file_path, 'r') as file:
        base64_data = file.read()

    # Decodifica los datos en base64
    image_data = base64.b64decode(base64_data)

    # Crea una imagen a partir de los datos decodificados
    image = Image.open(BytesIO(image_data))

    # Guarda la imagen en formato JPG
    # image.save('output.jpg', 'JPEG')

    # Muestra la imagen
    image.show()

    return base64_data

# Llama a la función con la ruta de tu archivo de texto


def enviar_peticion_http(url, data):
    # Define los datos que deseas enviar en el cuerpo de la solicitud
    payload = {'frame': data}

    # Realiza la petición HTTP POST
    response = requests.post(url, data=payload)

    # Imprime la respuesta del servidor
    print(response.text)

# Llama a la función con el enlace proporcionado y el string que deseas enviar
url = "http://192.168.163.193:8000/web/sendImg/"
xd = decode_base64_and_show_image('xd.txt')
print(xd)
data_to_send = xd

enviar_peticion_http(url, data_to_send)