use crate::traits::builder::Builder;

pub struct CliHandlerConfig {
  pub string_size: usize
}

impl Default for CliHandlerConfig {
  fn default() -> Self {
    Self {
      string_size: 128
    }
  }
}

pub struct CliHandlerConfigBuilder {
  string_size: Option<usize>
}

impl Builder<CliHandlerConfig> for CliHandlerConfigBuilder {

  fn new() -> Self {
    Self {
      string_size: None
    }
  }
  
  fn build(self) -> CliHandlerConfig {
    let cli_handle_config_defaults = CliHandlerConfig::default();

    CliHandlerConfig {
      string_size: self.string_size.unwrap_or(cli_handle_config_defaults.string_size)
    }
  }

}
