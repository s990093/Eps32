import os

def list_library_folders(folder):
    libraries = []
    for entry in os.listdir(folder):
        entry_path = os.path.join(folder, entry)
        if os.path.isdir(entry_path):
            libraries.append(entry)
    return libraries

def write_requirements_file(libraries, output_file):
    with open(output_file, 'w') as file:
        for lib in libraries:
            file.write(f"{lib}\n")

folder = '/Users/hungwei/Documents/Arduino/libraries'
output_file = 'requirements.txt'
libraries = list_library_folders(folder)

print("Libraries found in the folder:")
for lib in libraries:
    print(f"- {lib}")

write_requirements_file(libraries, output_file)
print(f"\nLibrary names have been written to {output_file}")
