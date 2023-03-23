#include <iostream>
#include <functional>

#include <vector>
#include <iterator>

class FuncClass
{
public:
	FuncClass() {}
	void operator()() { std::cout << "Operator "<< m <<"\n";}
	void operator()(int a) { std::cout << "a: " << a << "\n"; }
private:
	int m{ -1 };
};

void just_f()
{
	std::cout << "I'm just a function\n";
}

void some_f(const std::function<void()>& f)
{
	f();
}

int main()
{
	int some_var = 4;
	int another_var = 6;

	auto my_f = [=, &another_var]() mutable { some_var++; std::cout << "I'm a lambda function\n"; std::cout << "Some var in lambda " << some_var << "\n"; };
	my_f();
	std::cout << "Some var " << some_var << "\n";

	std::function<void()> another_f = []() { std::cout << "I'm another lambda function\n"; };

	some_f(another_f);

	some_f(my_f);

	some_f(just_f);

	FuncClass a;

	std::function<void()> arr[] = { just_f, my_f, another_f, a };	

	for (auto i = std::begin(arr); i != std::end(arr); ++i)
	{
		(*i)();
	}

	some_f(a);

	a();
	a(1);
	return 0;
}