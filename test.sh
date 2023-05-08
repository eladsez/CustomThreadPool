
echo '=================Coder Test================='

KEY=2
CHAR_SIZE=100000 # one hundred thousand characters
RED='\033[0;31m'
GREEN='\033[0;32m'

make all &> /dev/null

# Generate 1000 characters
#echo "Generating ${CHAR_SIZE} characters..."
#bash build/lipsum.sh characters $CHAR_SIZE > /tmp/to_enc

echo "Encrypting..."
TIMEFORMAT='Time elapsed for encryption: %R seconds.'
time {
./coder $KEY -e < /tmp/to_enc > /tmp/to_dec
}

if diff /tmp/to_enc /tmp/to_dec &> /dev/null; then
    echo -e "${RED}Test failed (to_enc and to_dec files are the same)"
    exit 1
fi

echo "Decrypting..."
#START=$SECONDS
TIMEFORMAT='Time elapsed for decryption: %R seconds.'
time {
./coder $KEY -d < /tmp/to_dec > /tmp/decrypted
}

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

#rm /tmp/to_enc /tmp/to_dec /tmp/decrypted
make clean > /dev/null
