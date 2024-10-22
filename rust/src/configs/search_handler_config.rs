use crate::traits::builder::Builder;

pub struct SearchHandlerConfig {
  prefix_size: usize,
  suffix_size: usize,
}

pub struct SearchHandlerConfigBuilder {
  prefix_size: Option<usize>,
  suffix_size: Option<usize>,
}

impl Builder<SearchHandlerConfig> for SearchHandlerConfigBuilder {
  fn new() -> Self {
    Self {
      prefix_size: None,
      suffix_size: None
    }
  }

  fn build(self) -> SearchHandlerConfig {
    SearchHandlerConfig {
      prefix_size: 
    }
  }

}
