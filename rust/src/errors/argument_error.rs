use core::error;
use std::fmt;

#[derive(Debug)]
pub struct ArgumentError(pub String);

impl fmt::Display for ArgumentError {
  fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
    write!(f, "{}", self.0)
  }
}

impl error::Error for ArgumentError {}

