import requests, json

                 auth_info = requests.get("https://graph.facebook.com/oauth/access_token?grant_type=client_credentials&client_id=your_client_id&client_secret=your_client_secret").text print(auth_info)
#access_token = auth_info.json()["access_token"]
#print(access_token)