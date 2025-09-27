#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <functional>
#include <optional>

template <typename T>
class Database {
    private:
	std::vector<std::unique_ptr<T>> entries;
    public:
	Database() = default;

	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;

	Database(Database&&) noexcept;
	Database operator=(Database&&) noexcept;

	template <typename... Args>
	void add(Arg&&... args);

	std::optional<T*> find(std::function<bool(const T&)> predicate) const;

	void printALL() const;

};

#include "Database.cpp"
