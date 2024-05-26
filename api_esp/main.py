from fastapi import Depends, FastAPI, HTTPException
from sqlalchemy.orm import Session
from database import SessionLocal, engine
import datetime
import models
import schemas
import crud

models.Base.metadata.create_all(bind=engine)
app = FastAPI()
app.include_router(schemas.router)

def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

@app.get("/")
def greet():
    return {"holy place": "empty"}

@app.get("/temperature/{location}")
def get_temperature(location: str, db: Session = Depends(get_db)):
    return {"values": crud.get_data(db, location=location)}

@app.post("/submit_temperature")
def submit_temperature(measurement: schemas.TemperatureValue, db: Session = Depends(get_db)):
    return crud.create_data(db=db, data=measurement)