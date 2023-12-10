import random
import json

data = {
    "n": 25,
    "Items": []
}

for i in range(1,data["n"]+1):
    index = i
    volume = random.randint(0, 20)
    mass = random.randint(0, 20)
    value = random.randint(0, 20)

    item = [
        f"index = {index}",
        f"volume = {volume}",
        f"mass = {mass}",
        f"value = {value}"
    ]

    data["Items"].append(item)

# Konwertuj do formatu JSON
json_data = json.dumps(data, indent=4)
print(json_data)
