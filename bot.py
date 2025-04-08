from flask import Flask, request, jsonify
from textblob import TextBlob
import google.generativeai as genai
import os

app = Flask(__name__)

# Set your regenerated Gemini API key here
GEMINI_API_KEY = "AIzaSyAvoZYkrgbmNCLqXkX3ggWHMI7V938VZEc"
genai.configure(api_key= "AIzaSyAvoZYkrgbmNCLqXkX3ggWHMI7V938VZEc")

# Load the Gemini model
model = genai.GenerativeModel('gemini-pro')

# Sentiment analysis function
def get_sentiment(text):
    analysis = TextBlob(text)
    polarity = analysis.sentiment.polarity
    if polarity > 0:
        return "positive 😊"
    elif polarity < 0:
        return "negative 😞"
    else:
        return "neutral 😐"

@app.route('/chat', methods=['POST'])
def chat():
    user_input = request.json.get("message", "")
    sentiment = get_sentiment(user_input)

    prompt = f"The user said: '{user_input}'\nThe sentiment is: {sentiment}.\nReply appropriately with a friendly tone."

    try:
        response = model.generate_content(prompt)
        return jsonify({
            "reply": response.text,
            "sentiment": sentiment
        })
    except Exception as e:
        return jsonify({
            "error": str(e)
        }), 500

if __name__ == '__main__':
    app.run(debug=True)
