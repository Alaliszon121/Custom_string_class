#include <stdio.h>
#include <string>
#include <vector>
#include <memory>

class String
{
private:
	std::unique_ptr<char[]> m_data = nullptr;
	size_t m_size = 0;

public:
	String()
	{
		printf("String constructor called!\n");
	}

	String(const String& other)
	{
		m_size = strlen(other.m_data.get());
		m_data = std::move(std::unique_ptr<char[]>(new char[m_size + 1]));
		memcpy(m_data.get(), other.m_data.get(), m_size + 1);

		printf("String copy-constructor called!\n");
	}

	String(const char* txt)
	{
		m_size = strlen(txt);
		m_data = std::move(std::unique_ptr<char[]>(new char[m_size + 1]));
		memcpy(m_data.get(), txt, m_size + 1);

		printf("String(txt) constructor called!\n");
	}

	String& operator+=(const char* txt)
	{
		size_t oldSize = m_size;
		size_t txtSize = strlen(txt);

		m_size += txtSize;
		
		std::unique_ptr<char[]> newMemory(new char[m_size + 1]);

		if(m_data)
		{
			memcpy(newMemory.get(), m_data.get(), oldSize);
		}

		memcpy(newMemory.get() + oldSize, txt, txtSize + 1);

		m_data = std::move(newMemory);

		return *this;
	}
};

constexpr size_t size = sizeof(std::weak_ptr<String>);

int main()
{
	char txt[] = "my text";
	const char* txt_c = "my text";

	String str = "my text";

	std::unique_ptr<String> uni_ptr;
	std::shared_ptr<String> ptr_str = std::make_unique<String>();
	std::weak_ptr<String> weak_ptr = ptr_str;

	std::vector<String> arr;
	arr.reserve(10);

	for (int i = 0; i < 10; i++)
	{
		printf("i=%i\n", i);
		arr.push_back("test");
		printf("\n");
	}

	str += " ha ha.";
	str += " New sentence.";

	return 0;
}
