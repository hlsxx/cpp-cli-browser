use std:: path::PathBuf;
use std::fs::{self, File};

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

  fn search_files_rec(&mut self, input_file_path: PathBuf) {
    if let Ok(entries) = fs::read_dir(input_file_path) {
      for entry in entries {
        println!("{:?}", entry);
      }
    }

    // if input_file_path.is_file() {
    //   self.files.push(input_file_path);
    // } else {
    //   self.search_files(input_file_path);
    // }
  }

  pub fn search_files(&mut self) {
    if self.input_file_path.is_file() {
      self.files.push(self.input_file_path.clone());
    } else {
      self.search_files_rec(self.input_file_path.clone());
    }

    println!("{:?}", self.files);
  }

  // pub fn init(&mut self) {
  //   self.search_files(self.input_file_path.clone());
  // }


}
