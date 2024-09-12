#include <bits/stdc++.h>

const std::string header_path = ".\\header.txt"; 
const std::string bottom_path = ".\\bottom.txt";
const std::string source_path = ".\\src";
const std::string output_path = ".\\templete.tex";
std::string readFileContent(const std::string& filePath) {  
    std::ifstream file(filePath);  
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());  
    return content;  
}  

int main() {
    
    freopen(output_path.c_str(), "w", stdout);
    
    auto find = [](auto self, const std::filesystem::path &path, int level) ->void {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {  
            std::string file_name = entry.path().filename().string();
            if(std::isdigit(file_name.front())) {
                file_name = file_name.substr(2);
            }
            std::string file_type(std::find(file_name.begin(), file_name.end(), '.'), file_name.end());
            file_name.erase(std::find(file_name.begin(), file_name.end(), '.'), file_name.end()); //去后缀
            std::string file_path = entry.path().string();
            std::replace(file_path.begin(), file_path.end(), '\\', '/');
            if (std::filesystem::is_regular_file(entry)) {
                file_type = std::string(file_type.begin() + 1, file_type.end());
                if(file_type == "tex") continue;
                auto dot_pos = std::find(file_path.rbegin(), file_path.rend(), '.') - file_path.rbegin();  
                file_path.erase(file_path.length() - dot_pos - 1);  
                std::cout << "\\";
                for(int i = 1; i <= level; ++i) {
                    std::cout << "sub";
                }
                std::cout << "section{" << file_name << "}" << std::endl; //章节
                std::cout << "\\input{" << file_path << ".tex" << "}" << std::endl; //注记
                std::cout << "\\lstinputlisting[style=" << file_type << "style]{" << file_path << '.' << file_type << "}" << std::endl;//文件 
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