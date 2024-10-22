use core::error;
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

  fn search_files_rec(
    &mut self,
    input_file_path: PathBuf
  ) -> Result<(), Box<dyn error::Error>> {
    if let Ok(entries) = fs::read_dir(input_file_path) {
      for entry in entries {
        let dir_path = entry?.path();

        if dir_path.is_file() {
          self.files.push(dir_path.clone());
        } else {
          self.search_files_rec(dir_path)?;
        }
      }
    }

    Ok(())
  }

  pub fn search_files(&mut self) -> Result<(), Box<dyn error::Error>> {
    if self.input_file_path.is_file() {
      self.files.push(self.input_file_path.clone());
    } else {
      self.search_files_rec(self.input_file_path.clone())?;
    }

    Ok(())
  }

}
