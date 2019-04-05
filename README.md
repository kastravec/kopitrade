# kopitrade
Explore and track stocks, see charts and information based on the IEX service

## How to use it?

## Requirements
### 1. Download, install Qt5.12 or higher (make sure to install QtWebEngine module and QtCreator)
### 3. You need an IEX cloud account - https://iexcloud.io
### 4. Create a json file - kopi-iexcloud.config in your home dir 
The json file should look like this:

~~~~~~~~
{
    "APIHostLive": "https://cloud.iexapis.com",
    "APILiveVersion": "beta",
    "Environment": 13, // 13 is for Live or 12 for Sandbox
    "PublicToken": "iex public token", 
    "SandboxToken": "iex sandbox token"
}
~~~~~~~~

## How to run it
### 1. Clone repo 
### 2. Launch QtCreator - Open project kopi.pro - build and run
