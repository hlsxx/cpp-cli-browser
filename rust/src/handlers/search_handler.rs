use std::path::PathBuf;

pub struct SearchHandler<'a> {
  files: Vec<PathBuf>,
  search: &'a str
}

