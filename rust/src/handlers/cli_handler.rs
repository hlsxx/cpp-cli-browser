use std::env;

use crate::{configs::cli_handler_config::{CliHandlerConfig, CliHandlerConfigBuilder}, traits::builder::Builder};

pub struct CliHandler {
  config: CliHandlerConfig
}

impl CliHandler {

  pub fn new() -> Self {
    Self {
      config: CliHandlerConfigBuilder::new().build()
    }
  }

  pub fn get_arguments(&self) -> () {
    let args = env::args();
    println!("{:?}", args);
  }

}
