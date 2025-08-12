from openai import OpenAI
from dotenv import load_dotenv
import os

load_dotenv()

secret = os.getenv("API-KEY")
client = OpenAI(api_key=secret)

def chatGPT_api(user_input: str) -> None:
	return client.responses.create(
		model="gpt-4.1",
		input=user_input
	).output_text