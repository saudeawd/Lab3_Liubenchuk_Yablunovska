#ifndef LAB1_STRINGS_MYSTRING_H_
#define LAB1_STRINGS_MYSTRING_H_

#include <string>
#include <iostream>

class my_str_t {
public:
    //! Створює стрічку із size копій літери initial
    //! capacity_m встановлює рівним або більшим за size
    //! Обробка помилок конструкторами:
    //! Не повинні заважати пропагуванню виключення std::bad_alloc.
    my_str_t(size_t size, char initial);

    //! Створює невизначену стрічку зазначеного розміру
    explicit my_str_t(size_t size);

    //! Створює стрічку з масиву символів
    my_str_t(size_t size, const char* str);

    //! Копіює вміст С-стрічки, вимоги до capacity_m -- ті ж, що вище
    explicit my_str_t(const char* cstr);

    //! Копіює стрічку С++, вимоги до capacity_m -- ті ж, що вище
    explicit my_str_t(const std::string& str);

    //! Конструктор копіювання
    my_str_t(const my_str_t& str);

    //! Оператор присвоєння
    //! Має повертати посилання на самого себе --
    //! на об'єкт, якому присвоювали
    my_str_t& operator=(const my_str_t& str);

    //! Advanced!
    //! Реалізація не є складною, але вимагає розуміння суті
    my_str_t(my_str_t&& str) noexcept;
    my_str_t& operator=(my_str_t&& str) noexcept;

    //! Обмінює вміст цієї стрічки з other, за допомогою
    //! обміну вказівників
    //! noexcept вказує, що функція ніколи не кидає виключень
    void swap(my_str_t& other) noexcept;

    //! Два варіанти оператора індексації -- для константних та
    //! неконстантних об'єктів
    //! Обробка помилок:
    //! Не перевіряє виходу за межі.
    char& operator[](size_t idx);
    const char& operator[](size_t idx) const;

    //! Те ж, що й оператори []
    //! Обробка помилок:
    //! Якщо idx >= size_m -- кидає виключення std::out_of_range.
    char& at(size_t idx);
    const char& at(size_t idx) const;

    //! Збільшує capacity до такого, що більший за new_capacity.
    //! capacity = new_capacity округлений вгору щоб ділитись на 16
    //! мінус 1 зарезервований для нульового символа.
    //! Якщо new_capacity менша за capacity_m -- не робить нічого
    //! Для збільшення -- виділяє новий блок пам'яті,
    //! копіює size_m байт -- фактичний вміст стрічки,
    //! у цей новий блок, звільняє старий блок, а
    //! вказівник на новий зберігає в data_m.
    //! Обробка помилок:
    //! Не повинні заважати пропагуванню виключення
    //! std::bad_alloc.
    void reserve(size_t new_capacity);

    //! Зменшує розмір до мінімального необхідного.
    //! Мінімально необхідний -- це size_m.
    //! Для оптимізації подальшого зростання стрічки,
    //! він може бути трохи більшим -- на розсуд реалізації.
    //! Обробка помилок:
    //! Не повинні заважати пропагуванню виключення
    //! std::bad_alloc.
    void shrink_to_fit();

    //! Змінює фактичний розмір стрічки.
    //! 1. Якщо новий розмір менший за старий -- лише оновлює
    //! значення в size_m.
    //! 2. Якщо new_size > size_m, але <= capacity_m,
    //! то змінює size_m і нові літери.
    //! 3. Якщо new_size > capacity_m, збільшує зарезервовану
    //! пам'ять за допомогою виклику reserve(), далі -- як в п. 2
    //! Обробка помилок:
    //! Не повинні заважати пропагуванню виключення
    //! std::bad_alloc.
    void resize(size_t new_size, char new_char = ' ');

    //! Очищає вміст стрічки -- для цього достатньо
    //! зробити size_m = 0.
    void clear();

    //! Вставляє передану стрічку типу my_str_t, чи літеру,
    //! чи С-стрічку, починаючи з літери idx,
    //! зсуваючи літеру з позиції idx і правіше праворуч.
    //! Обробка помилок:
    //! Якщо idx > size_m -- кидає виключення std::out_of_range
    void insert(size_t idx, const my_str_t& str);

    //! Ця функція -- служить для оптимізації, щоб не
    //! довелося спочатку створювати із літери c стрічку my_str_t, а
    //! потім вставляти. Навіть якщо компілятор зробив би це
    //! автоматично -- це повільно.
    void insert(size_t idx, char c);

    //! Аналогічна оптимізація для C-стрічок
    void insert(size_t idx, const char* cstr);

    //! Додає стрічку чи літеру в кінці стрічки.
    //! Обробка помилок:
    //! Не повинні заважати пропагуванню виключення
    //! std::bad_alloc.
    void append(const my_str_t& str);
    void append(char c);
    void append(const char* cstr);

    //! Видаляє size літер, починаючи з індексу begin.
    //! Літери праворуч від видаленого шматка зсуваються
    //! на size ліворуч.
    //! Обробка помилок:
    //! Якщо begin > size_m -- кидає виключення std::out_of_range.
    //! Але якщо стрічка містить менше символів для стирання,
    //! ніж потрібно -- це не помилка, видаляє всі до кінця.
    void erase(size_t begin, size_t size);

    //! Наступні функції повертають розмір стрічки та
    //! зарезервований блок пам'яті.
    //! Правильніше б назвати get_size() та get_capacity(),
    //! але історично в std::string прийнято
    //! так, то будемо наслідувати його
    size_t size() const noexcept;
    size_t capacity() const noexcept;

    //! Повертає вказівник на С-стрічку, яка відповідає
    //! цьому об'єкту. Якщо виділяти один зайвий байт,
    //! як описано в документації на конструтор, то їй
    //! достатньо зберегти нульовий байт у позиції
    //! data_m[size_m] і повернути data_m.
    const char* c_str() const;

    //! Функції find шукають вказану літеру чи стрічку,
    //! починаючи із idx. Якщо не знайдено, повертає
    //! константу my_str_t::not_found
    //! Обробка помилок:
    //! Якщо idx > size_m -- кидає виключення std::out_of_range.
    static constexpr size_t not_found = -1;
    size_t find(char c, size_t idx = 0) const;
    size_t find(const std::string& str, size_t idx = 0) const;
    size_t find(const char* cstr, size_t idx = 0) const;

    //! Скопіювати підстрічку, із begin включно,
    //! по begin+size не включно ([begin, begin+size)).
    //! Якщо end за межами початкової стрічки -- це не помилка,
    //! копіювати всі символи до кінця.
    //! beg має бути в її межах -- якщо begin>=size, це помилка.
    //! Обробка помилок:
    //! Якщо begin > size_m -- кидає виключення std::out_of_range.
    my_str_t substr(size_t begin, size_t size) const;

    //! Додатковий функціонал
    my_str_t& operator*=(size_t times);

    //! Визначені тут для inline-оптимізацій
    my_str_t& operator+=(const char c) {
        append(c);
        return *this;
    }

    my_str_t& operator+=(const char* cstr) {
        append(cstr);
        return *this;
    }

    my_str_t& operator+=(const my_str_t& str) {
        append(str);
        return *this;
    };

    //! Оператори порівняння.
    std::strong_ordering operator<=>(const my_str_t& str2) const;
    bool operator==(const my_str_t& str2) const;
    std::strong_ordering operator<=>(const char* cstr2) const;
    bool operator==(const char* cstr2) const;

    void write(const char* buffer, size_t begin, size_t size) const;

    //! Деструктор.
    ~my_str_t();

private:
    size_t size_m{0}; // Фактичний розмір стрічки
    size_t capacity_m{0}; // Розмір блока
    // Рекомендовано, щоб блок пам'яті містив на 1 байт більше,
    // ніж capacity_m чи максимальний size_m -- це робить
    // реалізацію c_str() тривіальною.
    char* data_m{nullptr}; // Вказівник на блок пам'яті
}; // Оголошення класу закінчилося тут!

//! Оператори вводу-виводу.
//! Увага, в загальному випадку, operator<< і operator>> мають
//! бути симетричними: оператор вводу повинен вміти прочитати те,
//! що вивів оператор виводу.
//! Для стрічок ця умова дещо спрощена -- operator<< має вивести
//! всю стрічку, а operator>> -- пропустити всі whitespace,
//! та прочитати одне слово -- до наступного whitespace.
//! Детальніше -- див. поведінку operator>> для std::string та
//! маніпулятор типу std::skipws.
inline std::ostream& operator<<(std::ostream& stream, const my_str_t& str) {
    stream << str.c_str();
    return stream;
}

//! Повинен пропустити всі whitespace, та прочитати одне слово --
//! до наступного whitespace.
//! Тут, для простоти, варто читати посимвольно.
//! УВАГА! В загальному випадку, читати по одному символу --
//! надміру повільно! Але тут це єдиний простий спосіб.
std::istream& operator>>(std::istream& stream, my_str_t& str);

//! Функція, яка читає потік до символу \n і зберігає її в str,
//! очистивши стрічку перед тим.
std::istream& readline(std::istream& stream, my_str_t& str);

//! Додаткові оператори
my_str_t operator+(const my_str_t& str, char c);
my_str_t operator+(char c, const my_str_t& str);
my_str_t operator+(const my_str_t& str1, const char* cstr2);
my_str_t operator+(const char* cstr1, const my_str_t& str2);
my_str_t operator+(const my_str_t& str1, const my_str_t& str2);
my_str_t operator*(const my_str_t& str1, size_t times);

inline my_str_t operator*(const size_t times, const my_str_t& str) {
    return str * times;
};

#endif
