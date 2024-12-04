if [[ "$OSTYPE" == "linux-gnu"* ]]; then
  apt install libcunit1 libcunit1-doc libcunit1-dev gcc
  gcc RVC_Cunit_test.c -o unit_test.out -L/usr/lib/x86_64-linux-gnu -lcunit
elif [[ "$OSTYPE" == "darwin"* ]]; then
  brew install cunit gcc
  gcc RVC_Cunit_test.c -o unit_test.out -I/opt/homebrew/include -L/opt/homebrew/lib -lcunit
elif [[ "$OSTYPE" == "cygwin" || "$OSTYPE" == "msys" ]]; then
  echo "Windows are not supproted."
else
  echo "Unknown OS"
fi

./unit_test.out