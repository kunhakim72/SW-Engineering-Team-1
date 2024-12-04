if [[ "$OSTYPE" == "linux-gnu"* ]]; then
  gcc -o test_math_utils test_math_utils.c math_utils.c -lcunit
elif [[ "$OSTYPE" == "darwin"* ]]; then
  gcc RVC_Cunit_test.c -o unit_test.out -I/opt/homebrew/include -L/opt/homebrew/lib -lcunit
elif [[ "$OSTYPE" == "cygwin" || "$OSTYPE" == "msys" ]]; then
  echo "Windows are not supproted."
else
  echo "Unknown OS"
fi

./run.sh