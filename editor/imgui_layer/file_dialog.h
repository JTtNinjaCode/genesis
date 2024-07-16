#pragma once
#include <genesis.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>

#include <algorithm>
#include <ctime>
#include <filesystem>
#include <functional>
#include <stack>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
namespace ImGuiExtend {
class FileDialog {
 public:
  static inline FileDialog& Instance() {
    static FileDialog instance;
    return instance;
  }
  enum class DialogType { kReadFile, kReadDirectory, kSave };
  struct FileTreeNode {
    FileTreeNode(const std::wstring& path) : path(std::filesystem::path(path)) {}
    FileTreeNode(const std::string& path) : path(std::filesystem::u8path(path)) {}

    std::filesystem::path path;
    bool read = false;
    std::vector<FileTreeNode*> children;
  };
  struct FileData {
    FileData(const std::filesystem::path& path);

    std::filesystem::path path;
    bool is_directory;
    size_t size;
    time_t date_modified;

    bool has_icon_preview = false;
    std::shared_ptr<genesis::Texture2D> icon_preview;
    uint8_t* icon_preview_data = nullptr;
    int icon_preview_width = 0, icon_preview_height = 0;
  };
  bool Save(const std::string& key, const std::string& title, const std::string& filter,
            const std::string& starting_dir = "");
  bool Open(const std::string& key, const std::string& title, const std::string& filter, bool is_multiselect = false,
            const std::string& starting_dir = "");
  bool IsDone(const std::string& key);
  void Close();
  inline bool HasResult() { return !result_.empty(); }
  inline const std::filesystem::path& GetResult() { return result_[0]; }
  inline const std::vector<std::filesystem::path>& GetResults() { return result_; }

  inline void SetZoom(float zoom) {
    zoom_ = std::clamp(zoom, 1.0f, 5.0f);
    RefreshPreviewIcon();
  }
  inline float GetZoom() const { return zoom_; }

 private:
  FileDialog();
  ~FileDialog();

  void Select(const std::filesystem::path& path, bool is_ctrl_down = false);
  bool Finalize(const std::string& filename = "");
  void ParseFilter(const std::string& filter);

  std::shared_ptr<genesis::Texture2D> GetIcon(const std::filesystem::path& path);
  void ClearIcons();

  void LoadPreviewIcon();
  void StopPreviewIconLoader();
  void ClearPreviewIcon();
  void RefreshPreviewIcon();

  void ClearTree(FileTreeNode* node);
  void SetDirectory(const std::filesystem::path& path, bool add_history = true);
  void SortContent(unsigned int sort_column, unsigned int sort_direction);

  void RenderTree(FileTreeNode* node);
  void RenderContent();
  void RenderPopups();
  void RenderFileDialog();

  std::vector<int> icon_indices_;
  std::vector<std::filesystem::path> icon_file_paths_;
  std::unordered_map<std::filesystem::path, std::shared_ptr<genesis::Texture2D>> icons_;

  std::thread* preview_loader_;
  bool preview_loader_running_;

  std::string current_key_;
  std::string current_title_;
  std::filesystem::path current_directory_;
  bool is_multiselect_;
  bool is_open_;
  DialogType type_;
  std::stack<std::filesystem::path> back_history_, forward_history_;
  float zoom_;

  char input_textbox_[512];
  char path_buffer_[512];
  char new_entry_buffer_[512];
  char search_buffer_[128];

  std::vector<std::filesystem::path> selections_;
  int selected_file_item_;
  std::string filter_;
  unsigned int sort_column_;
  unsigned int sort_direction_;
  std::vector<std::filesystem::path> result_;
  std::vector<FileData> content_;
  std::vector<FileTreeNode*> tree_cache_;
  std::vector<std::vector<std::string>> filter_extensions_;
  size_t filter_selection_index_;
};

}  // namespace ImGuiExtend