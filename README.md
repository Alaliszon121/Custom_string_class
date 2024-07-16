# Dokumentacja klasy `String`

## Opis
Niestandardową implementacja klasy string w C++. Zawiera konstruktor domyślny, konstruktor kopiujący, konstruktor inicjalizujący z ciągu znaków (`const char*`), oraz operator przypisania z dodaniem ciągu znaków. Klasa korzysta z inteligentnych wskaźników (`std::unique_ptr<char[]>`) do zarządzania pamięcią dynamiczną.

## Składnia

### Deklaracja Klasy

```cpp
class String
{
private:
    std::unique_ptr<char[]> m_data = nullptr;
    size_t m_size = 0;

public:
    String();
    String(const String& other);
    String(const char* txt);
    String& operator+=(const char* txt);
};
```

## Szczegóły Implementacji

### Składowe Prywatne

- `std::unique_ptr<char[]> m_data`: Wskaźnik na dynamicznie alokowaną tablicę znaków.
- `size_t m_size`: Przechowuje rozmiar ciągu znaków.

### Konstruktory i Metody Publiczne

#### Konstruktor Domyślny

```cpp
String()
{
    printf("String constructor called!\n");
}
```

Tworzy pusty obiekt `String`.

#### Konstruktor Kopiujący

```cpp
String(const String& other)
{
    m_size = strlen(other.m_data.get());
    m_data = std::move(std::unique_ptr<char[]>(new char[m_size + 1]));
    memcpy(m_data.get(), other.m_data.get(), m_size + 1);

    printf("String copy-constructor called!\n");
}
```

Tworzy kopię innego obiektu `String`.

#### Konstruktor Inicjalizujący z `const char*`

```cpp
String(const char* txt)
{
    m_size = strlen(txt);
    m_data = std::move(std::unique_ptr<char[]>(new char[m_size + 1]));
    memcpy(m_data.get(), txt, m_size + 1);

    printf("String(txt) constructor called!\n");
}
```

Inicjalizuje obiekt `String` z ciągu znaków typu `const char*`.

#### Operator Przypisania z Dodaniem Ciągu Znaków

```cpp
String& operator+=(const char* txt)
{
    size_t oldSize = m_size;
    size_t txtSize = strlen(txt);

    m_size += txtSize;

    std::unique_ptr<char[]> newMemory(new char[m_size + 1]);

    if (m_data)
    {
        memcpy(newMemory.get(), m_data.get(), oldSize);
    }

    memcpy(newMemory.get() + oldSize, txt, txtSize + 1);

    m_data = std::move(newMemory);

    return *this;
}
```

Dodaje ciąg znaków do istniejącego obiektu `String` i zwraca referencję do bieżącego obiektu.

## Przykład Użycia

```cpp
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
```

### Komentarze do Przykładu

- Tworzenie instancji klasy `String` z użyciem literału znakowego.
- Tworzenie inteligentnych wskaźników (`std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`) zarządzających obiektem `String`.
- Dodawanie elementów do wektora typu `String`.
- Użycie operatora `+=` do dodania ciągu znaków do obiektu `String`.

## Uwagi

- Klasa `String` używa `std::unique_ptr<char[]>` do zarządzania pamięcią, co zapewnia automatyczne zwalnianie pamięci i unikanie wycieków pamięci.
- Operator `+=` wykonuje dynamiczne alokowanie nowej pamięci i kopiowanie istniejących danych oraz dodawanych znaków, co jest efektywne dla małych operacji, ale może być kosztowne dla dużych ciągów znaków.
- Kopiowanie i przenoszenie obiektów `String` jest bezpieczne dzięki użyciu mechanizmu inteligentnych wskaźników.

## Podsumowanie

Klasa `String` przedstawia podstawową implementację dynamicznego ciągu znaków w C++ z wykorzystaniem inteligentnych wskaźników. Dzięki konstruktorom, metodom i operatorowi przypisania umożliwia efektywne zarządzanie pamięcią oraz operacje na ciągach znaków.
