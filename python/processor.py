with open("version.yaml", "w") as file:
    try:
        file.write("version: \"2.0.0\"")
        file.close()
    
        print("Successfully created 'version.yaml'")
    except Exception as e:
        print(f"Error: {e}")
