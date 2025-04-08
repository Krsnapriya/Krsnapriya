import random

def check_password(password):
    length = len(password)
    has_letters = False
    has_numbers = False
    has_special = False
    special_chars = "!@#$%&*ˆ"
    
    for char in password:
        if char.isalpha():
            has_letters = True
        elif char.isdigit():
            has_numbers = True
        elif char in special_chars:
            has_special = True
    
    if length < 6 or (has_letters and not has_numbers and not has_special) or \
       (has_numbers and not has_letters and not has_special):
        return "Weak"
    elif length > 10 and has_letters and has_numbers and has_special:
        return "Strong"
    elif 6 <= length <= 10 and has_letters and has_numbers and not has_special:
        return "Moderate"
    return "Moderate"

def make_passwords(min_length, max_length, use_letters, use_numbers, use_special, target_type):
    if min_length > max_length:
        print("Minimum length should be less than maximum length.")
        return []
    
    characters = ""
    if use_letters:
        characters += "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    if use_numbers:
        characters += "0123456789"
    if use_special:
        characters += "!@#$%&*ˆ"
    
    if not characters:
        print("Choose at least one type of character.")
        return []
    
    
    passwords = []
    for _ in range(5):
        length = random.randint(min_length, max_length)
        password = ""
        for _ in range(length):
            password += random.choice(characters)
        if check_password(password) == target_type:
            passwords.append(password)
    
    return passwords


min_len = int(input("Shortest length you want: "))
max_len = int(input("Longest length you want: "))
target = input("Choose a type? (Weak/Moderate/Strong): ").capitalize()
letters = input("Use letters? (yes/no): ").lower() == "yes"
numbers = input("Use numbers? (yes/no): ").lower() == "yes"
special = input("Use special characters? (yes/no): ").lower() == "yes"


password_list = make_passwords(min_len, max_len, letters, numbers, special, target)
if password_list:
    print(f"Here are some {target} passwords:")
    for i, pwd in enumerate(password_list, 1):
        print(f"{i}. {pwd}")
else:
    print("No passwords generated.")