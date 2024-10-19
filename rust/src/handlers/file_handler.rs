use std:: path::PathBuf;
use std::fs::File;

pub struct FileHandler {
  input_file_path: PathBuf,
  files: Vec<PathBuf>
}

impl FileHandler {

  pub fn new(input_file_path: PathBuf) -> Self {
    Self {
      input_file_path,
      files: Vec::new()
    }
  }

  pub fn init(&mut self) {
    self.search_files(self.input_file_path.clone());
  }

  pub fn search_files(&mut self, input_file_path: PathBuf) {
    if input_file_path.is_file() {
      self.files.push(input_file_path);
    } else {
      // self.search_files(input_file_path);
    }
  }

}
