use std::io::{BufReader,BufRead};
use std::fs::File;


async fn send_request(url:&str) -> Result<(),reqwest::Error>{
    let response = reqwest::get(url)
        .await?;

    let text = response.text().await?;

    println!("{}", text);

    Ok(())
}



#[tokio::main]
async fn main(){
    let url = "https://google.com/";
    let file = File::open("dirs.txt").expect("Cannot open file");
    let reader = BufReader::new(file);
    for line in reader.lines() {
        let line = line.expect("Cannot read line");
        let new_url = format!("{}{}", url, line);
        let response = send_request(&new_url).await;
        println!("[+]Respone: {:?}",response);

    }
}
