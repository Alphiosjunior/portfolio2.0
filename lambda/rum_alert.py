import json
import gzip
import base64
import boto3
from datetime import datetime

sns = boto3.client('sns', region_name='eu-north-1')
TOPIC_ARN = 'arn:aws:sns:eu-north-1:998072949274:rum-visitor-alerts'

def lambda_handler(event, context):
    payload = json.loads(gzip.decompress(base64.b64decode(event['awslogs']['data'])))
    
    for log_event in payload['logEvents']:
        try:
            data = json.loads(log_event['message'])
            
            if data.get('event_type') == 'com.amazon.rum.page_view_event':
                metadata = data.get('metadata', {})
                
                location = metadata.get('localityName', 'Unknown')
                subdivision = metadata.get('subdivisionCode', 'Unknown')
                country = metadata.get('countryCode', 'Unknown')
                device = metadata.get('deviceType', 'Unknown')
                browser = metadata.get('browserName', 'Unknown')
                os = metadata.get('osName', 'Unknown')
                page = metadata.get('pageId', '/')
                
                message = f"""New visitor on alphiosjunior.co.za!

Location: {location}, {subdivision}, {country}
Device: {device}
Browser: {browser} on {os}
Page: {page}
Time: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}"""
                
                sns.publish(
                    TopicArn=TOPIC_ARN,
                    Message=message,
                    Subject='New Site Visitor'
                )
        except Exception as e:
            print(f"Error: {e}")
    
    return {'statusCode': 200}
