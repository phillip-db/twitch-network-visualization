import requests
import pandas as pd

df = pd.read_csv(r'C:\Users\saaga\PycharmProjects\TwitchDataAccess\english_data\english_target.csv')

id_list = df['id'].to_list()

id_chunks = [id_list[x:x + 100] for x in range(0, len(id_list), 100)]

headers = {
    'Authorization': '', #Removed for privacy/safety
    'Client-Id': '', #Removed for privacy/safety
}

usernames = {}
params = {'id': []}
for i in range(len(id_chunks)):
    params["id"] = id_chunks[i]
    response = requests.get('https://api.twitch.tv/helix/users', headers=headers, params=params)

    n = len(response.json()["data"])
    for j in range(n):
        name = response.json()["data"][j].get('display_name')
        twitch_id = int(response.json()["data"][j].get('id'))
        usernames[twitch_id] = name

ordered_usernames = []

for i in range(len(id_list)):
    cur_id = id_list[i]
    if cur_id in usernames:
        ordered_usernames.append(usernames.get(cur_id))
    else:
        ordered_usernames.append("---")

df['username'] = ordered_usernames

df.to_csv('modified_english_target.csv')
