import requests

response = requests.post(
	"http://127.0.0.1:8000/", 
	json={"input": "Hello there!"},
	stream=True 
)

for chunk in response.iter_lines():
	print(chunk)