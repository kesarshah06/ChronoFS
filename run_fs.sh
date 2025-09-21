g++ -std=c++17 -O2 -Wall main.cpp -o main

if [ $? -ne 0 ]; then
    echo "Compilation failed. Fix errors and try again."
    exit 1
fi

echo "Starting the FileSystem shell..."
./main
