template <typename T>
Database<T>::Database(Datbase&& other) noexcept
	: entries(std::move(other.entries)) {

}
