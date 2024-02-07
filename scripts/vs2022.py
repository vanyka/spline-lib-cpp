import os

GENERATOR = 'Visual Studio 17 2022'

os.system(f'cmake -G "{GENERATOR}" -S .. -B ../_builds/vs2022')

input("Press Enter to continue...")
