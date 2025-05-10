#include <iostream>

class smallobj {
  public:
    explicit smallobj(int a) : a(a) { std::cout << __LINE__ << std::endl; }

    ~smallobj() = default;

    smallobj(const smallobj &o) { a = o.a + 2; }

    void print_a() { std::cout << this->a << std::endl; }

    smallobj &operator=(const smallobj &o) {
        a = o.a + 10;
        return *this;
    }

  private:
    int a;
};

int main(void) {

    smallobj a(1);
    smallobj b = a;
    smallobj c = a = b;

    a.print_a();
    {
        int a = 0;
        std::cout << "cout " << a << std::endl;
    }
    return 0;
}
