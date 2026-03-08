
#!/bin/bash


GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

PASSED=0
FAILED=0

test_vbc() {
	local expr="$1"
	local expected="$2"    
	result=$(./a.out "$expr" 2>&1)
	exit_code=$?
	if [ $exit_code -eq 0 ] && [ "$result" = "$expected" ]; then
        	echo -e "${GREEN}✓${NC} '$expr' → $result (esperado: $expected)"
	        ((PASSED++))
	else
		echo -e "${RED}✗${NC} '$expr' → $result (esperado: $expected)"
		((FAILED++))
	fi
}

test_error() {
	local expr="$1"
	./a.out "$expr" > /dev/null 2>&1
	exit_code=$?
		        
        if [ $exit_code -eq 1 ]; then
		echo -e "${GREEN}✓${NC} '$expr' → Error detectado correctamente"
		((PASSED++))
	else
		echo -e "${RED}✗${NC} '$expr' → Debería dar error"
		((FAILED++))
	fi
}

echo "=== Tests básicos ==="
test_vbc "1" "1"
test_vbc "5" "5"
test_vbc "9" "9"

echo ""
echo "=== Sumas ==="
test_vbc "2+3" "5"
test_vbc "1+2+3" "6"
test_vbc "5+0" "5"
test_vbc "1+1+1+1+1" "5"

echo ""
echo "=== Multiplicaciones ==="
test_vbc "2*3" "6"
test_vbc "3*4" "12"
test_vbc "2*2*2" "8"
test_vbc "5*0" "0"

echo ""
echo "=== Precedencia (+ vs *) ==="
test_vbc "2+3*4" "14"
test_vbc "3*4+5" "17"
test_vbc "1+2*3+4" "11"
test_vbc "2*3+4*5" "26"

echo ""
echo "=== Paréntesis ==="
test_vbc "(1)" "1"
test_vbc "(2+3)" "5"
test_vbc "(2+3)*4" "20"
test_vbc "2*(3+4)" "14"
test_vbc "(1+2)*(3+4)" "21"

echo ""
echo "=== Paréntesis anidados ==="
test_vbc "((1))" "1"
test_vbc "(((3)))" "3"
test_vbc "((2+3)*4)" "20"
test_vbc "(2*(3+4))" "14"
test_vbc "((1+2)*(3+4))" "21"
test_vbc "(((((2+2)*2+2)*2+2)*2+2)*2+2)*2" "188"

echo ""
echo "=== Expresiones complejas ==="
test_vbc "1+2+3+4+5" "15"
test_vbc "1*2*3*4" "24"
test_vbc "9+8*7+6*5+4*3+2*1" "109"
test_vbc "(1+1)*(2+2)*(3+3)" "48"
test_vbc "2*3+(2+3)" "11"

echo ""
echo "=== Tests del subject ==="
test_vbc "1" "1"
test_vbc "2+3" "5"
test_vbc "3*4+5" "17"
test_vbc "3+4*5" "23"
test_vbc "(3+4)*5" "35"
test_vbc "1+2+3+4+5" "15"

echo ""
echo "=== Tests de errores (deben fallar) ==="
test_error "1+"
test_error "1+2)"
test_error "(1+2"
test_error "((1+2)"
test_error "1+x"
test_error "a+b"
test_error "()"
test_error "(*2)"
test_error "+1"
test_error "1+2+3+4+5)"

echo ""
echo "=================================="
echo -e "${GREEN}PASSED: $PASSED${NC}"
echo -e "${RED}FAILED: $FAILED${NC}"
echo "=================================="

if [ $FAILED -eq 0 ]; then
	echo -e "${GREEN}¡Todos los tests pasaron! 🎉${NC}"
	exit 0
else
	echo -e "${RED}Algunos tests fallaron${NC}"
	exit 1
fi
