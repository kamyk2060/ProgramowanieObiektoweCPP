
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Song {
public:
    std::wstring artist;
    std::wstring title;

    Song(const std::wstring& a, const std::wstring& t) : artist(a), title(t) {
        std::wcout << L"Konstruktor: " << artist << L" - " << title << L"\n";
    }
    ~Song() {
        std::wcout << L"Destruktor:  " << artist << L" - " << title << L"\n";
    }
};

template <typename T>
std::unique_ptr<T> SongFactory(const std::wstring& artist, const std::wstring& title) {
    return std::make_unique<T>(artist, title);
}

int main() {
    auto song = SongFactory<Song>(L"Michael Jackson", L"Beat It");
    std::wcout << L"song trzyma: " << song->artist << L" - " << song->title << L"\n\n";

    std::vector<std::unique_ptr<Song>> songs;
    songs.push_back(SongFactory<Song>(L"B'z", L"Juice"));
    songs.push_back(SongFactory<Song>(L"Namie Amuro", L"Funky Town"));
    songs.push_back(SongFactory<Song>(L"Ayumi Hamasaki", L"Poker Face"));

    std::wcout << L"\nZawartosc vectora:\n";
    // Trzeba uzyc referencji, bo unique_ptr nie da sie kopiowac.
    for (const auto& s : songs) {
        std::wcout << L"  " << s->artist << L" - " << s->title << L"\n";
    }

    std::wcout << L"\nKoniec main - destruktory:\n";
    return 0;
}
