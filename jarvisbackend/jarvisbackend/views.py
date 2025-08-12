from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
import json
from . import chat_api
import time

@csrf_exempt
def handle_input(request):
	if request.method != 'POST':
		return HttpResponse("Only POST allowed", status=405)

	print("Message recieved! Generating response...\n\n")

	req = json.loads(request.body)
	user_input = req["input"]
	gpt_answer = chat_api.chatGPT_api(user_input)
	response = json.dumps({"status": "complete", "response": gpt_answer})

	return HttpResponse(response, status=200)