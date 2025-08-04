template <typename T>
Database<T>::Database(Datbase&& other) noexcept
	: entries(std::move(other.entries)) {

}

template <typename T>
template <typename... Args>
void Database<T>::add(Args&&... args) {
	entries.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
}


template <typename T>
void Database<T>::printALL() const {
	std::cout << "==== Database Contains ====" << std::endl;
	for (const auto& entry : entries) {
		std::cout << *entry << std::endl;
	}
	std::cout << "===========================" << std::endl;
}

template <typename T>
std::optional<T*> Database<T>::find(std::function<bool(const T&) predicate) const {
	

}

