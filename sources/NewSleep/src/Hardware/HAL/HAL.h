// 2024/03/01 22:24:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct ModeClock
{
    enum E
    {
        Low,        // Низкая частота, на которую переключаемся перед заходом в спящий режим
        Sleep,      // Спящий режим
        Hi,         // Частота 52МГц, в которую переходим по выходу из спящего режима
        Count
    };

    static void Set(E);

    static void LeaveSleep();

    static bool IsSleep() { return current == Sleep; }
    static bool IsLow()   { return current == Low; }
    static bool IsHi()    { return current == Hi; }

private:

    static E current;
};


namespace HAL
{
    void Init();

    void DeInit();
}


// Для приёмника
namespace HAL_TIM2
{
    void Init();

    void Start();
}


namespace HAL_ROM
{
    static const uint ADDRESS_BEGIN = 0x8000000;
    static const uint SIZE_PAGE = 1024;
    static const uint NUM_PAGES = 64;

    static const int PAGE_FOR_JOURNAL = 63;

    void Init();

    // Стиреть страницу от 0 до 63
    void ErasePage(int);

    uint AddressPage(int);

    // address должен быть кратен 4
    void WriteBuffer(uint address, const void *buffer, int size);

    // address должен быть кратен 4
    void ReadBuffer(uint address, void *buffer, int size);
}
