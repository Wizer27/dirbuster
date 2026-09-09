use std::io;



async fn send_request() -> Result<(),reqwest::Error>{
    let response = reqwest::get("https://httpbin.org/get")
        .await?;

    let text = response.text().await?;

    println!("{}", text);

    Ok(())
}



#[tokio::main]
async fn main(){
    let response = send_request().await;
    println!("{:?}",response);
}
