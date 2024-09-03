#include <bits/stdc++.h>

const std::string header_path = ".\\header.txt"; 
const std::string bottom_path = ".\\bottom.txt";
const std::string source_path = ".\\src";

std::string readFileContent(const std::string& filePath) {  
    std::ifstream file(filePath);  
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());  
    return content;  
}  

int main() {
    
    freopen("templete.tex", "w", stdout);
    
    auto find = [](auto self, const std::filesystem::path &path, int level) ->void {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {  
            std::string file_name = entry.path().filename().string();
            if(std::isdigit(file_name.front())) {
                file_name = file_name.substr(2);
            }
            file_name.erase(std::find(file_name.begin(), file_name.end(), '.'), file_name.end()); //去后缀
            std::string file_path = entry.path().string();
            std::replace(file_path.begin(), file_path.end(), '\\', '/');
            if (std::filesystem::is_regular_file(entry)) {
                std::cout << "\\";
                for(int i = 1; i <= level; ++i) {
                    std::cout << "sub";
                }
                std::cout << "section{" << file_name << "}" << std::endl;  
                std::cout << "\\lstinputlisting[style=cppstyle]{" << file_path << "}" << std::endl; 
            } else if (std::filesystem::is_directory(entry)) {  
                std::cout << "\\";
                for(int i = 1; i <= level; ++i) {
                    std::cout << "sub";
                }
                std::cout << "section{" << file_name << "}" << std::endl;  
                self(self, entry.path(), level + 1);
            }  
        } 
    };
    std::cout << readFileContent(header_path) << std::endl;
    find(find, source_path, 0);
    std::cout << readFileContent(bottom_path) << std::endl;
    return 0;
}