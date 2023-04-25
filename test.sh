
echo '=================Coder Test================='

KEY=2
RED='\033[0;31m'
GREEN='\033[0;32m'

make all &> /dev/null

# Generate 1000 characters
echo "Generating 1000 characters..."
bash build/lipsum.sh characters 1000 > /tmp/to_enc

echo "Encrypting..."
./Coder $KEY -e < /tmp/to_enc > /tmp/to_dec
echo "Decrypting..."
./Coder $KEY -d < /tmp/to_dec > /tmp/decrypted

# check if the files exists
if [ ! -f /tmp/to_enc ] || [ ! -f /tmp/to_dec ] || [ ! -f /tmp/decrypted ]; then
    make clean
    echo -e "${RED}Test failed (files not exists)"
    exit 1
fi

# check if the size of the files is bigger than 0
if [ ! -s /tmp/to_enc ] || [ ! -s /tmp/to_dec ] || [ ! -s /tmp/decrypted ]; then
    make clean
    echo -e "${RED}Test failed (files are empty)"
    exit 1
fi

if diff /tmp/to_enc /tmp/decrypted; then
    echo -e "${GREEN} Test passed"
else
    echo -e "${RED}Test failed"
fi

rm /tmp/to_enc /tmp/to_dec /tmp/decrypted
make clean > /dev/null