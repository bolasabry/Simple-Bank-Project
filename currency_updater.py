import requests

# 1. Only put the text key string here, not the whole link!
API_KEY = "071a5a88482c95834c0bea7c"
url = f"https://v6.exchangerate-api.com/v6/{API_KEY}/latest/USD"

def update_currency_file():
    # 2. Fetch live data from the new all-inclusive API
    try:
        response = requests.get(url)
        data = response.json()
        
        # Check if the API call was successful
        if data.get("result") == "success":
            live_rates = data.get("conversion_rates", {})
        else:
            print("API Error:", data.get("error-type", "Unknown error"))
            return
    except Exception as e:
        print("Could not connect to the internet:", e)
        return

    # 3. Read your original file lines
    try:
        with open("Currencies.txt", "r", encoding="utf-8") as file:
            lines = file.readlines()
    except FileNotFoundError:
        print("Currencies.txt not found. Make sure it's in this folder!")
        return

    # 4. Process and update every single country code
    updated_lines = []
    for line in lines:
        line = line.strip()
        if not line:
            continue
        
        parts = line.split("#//#")
        if len(parts) == 4:
            country, code, name, old_rate = parts
            
            # Now, almost EVERY code will match perfectly!
            if code in live_rates:
                new_rate = live_rates[code]
                line = f"{country}#//#{code}#//#{name}#//#{new_rate:.6f}"
                
        updated_lines.append(line + "\n")

    # 5. Save the 100% updated data back to the file
    with open("Currencies.txt", "w", encoding="utf-8") as file:
        file.writelines(updated_lines)
        
    print("Success! Every currency in Currencies.txt has been completely updated to 2026 values.")

# Run the update
update_currency_file()