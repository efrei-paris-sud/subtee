from flask import Flask
from flask_restful import Api, Resource, reqparse
from googletrans import Translator
import logging

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

api.add_resource(Translation, "/translate")

app.run(debug=True, host='0.0.0.0')