from flask import Flask, request
from flask_restful import Api, Resource, reqparse
from googletrans import Translator
import logging
import werkzeug
import speech_recognition as sr
from os import path

app = Flask(__name__)
api = Api(app)

class Translation(Resource):
    def post(self):
        parser = reqparse.RequestParser()
        parser.add_argument("string", required=True)
        parser.add_argument("lang_src", required=True)
        parser.add_argument("lang_dest", required=True)
        args = parser.parse_args()

        translator = Translator()
        try:
            translation = translator.translate(args['string'], src=args['lang_src'], dest=args['lang_dest'])
        except ValueError:
            return 'Cannot Translate', 409

        print("/translate : '{}' [{}] -> '{}' [{}]".format(
            args['string'],
            args['lang_src'],
            translation.text,
            args['lang_dest']
        ))

        rtn = translation.text

        return rtn, 200

class SpeechToText(Resource):
    def post(self):
        audioName = "bonjour-thomas.wav"
        sourceLanguage = "fr"

        r = sr.Recognizer()
        audioFile = path.join(path.dirname(path.realpath(__file__)), "audios/", audioName)

        with sr.AudioFile(audioFile) as source:
            audio = r.record(source)  # read the entire audio file
        try:
            # to use another API key, use `r.recognize_google(audio, key="GOOGLE_SPEECH_RECOGNITION_API_KEY")`
            return r.recognize_google(audio, language=sourceLanguage), 200
        except sr.UnknownValueError:
            print("Google Speech Recognition could not understand audio")
            return "Erreur 1", 500
        except sr.RequestError as e:
            print("Could not request results from Google Speech Recognition service; {0}".format(e))
            return "Erreur 2", 500

        # parse = reqparse.RequestParser()
        # parse.add_argument('audio', type=werkzeug.FileStorage, location='files')
        # args = parse.parse_args()

        #stream = args['audio'].stream

        #print(request.get_data())
        #wav_file = wave.open(stream, 'rb')
        # signal = wav_file.readframes(-1)
        # signal = np.fromstring(signal, 'Int16')
        # fs = wav_file.getframerate()
        #wav_file.close()

api.add_resource(Translation, "/translate")
api.add_resource(SpeechToText, "/speech-to-text")

app.run(debug=True, host='0.0.0.0')
