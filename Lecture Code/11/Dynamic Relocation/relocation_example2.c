// relocation_example2.c
void print_global();  // Declaration of external function

int main() {
    print_global();  // Call function from shared library
    return 0;
}
