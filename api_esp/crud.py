from sqlalchemy.orm import Session
import datetime
import models
import schemas

def get_data(db: Session, location: str = ""):
    return [i.value for i in db.query(models.Data).filter(models.Data.location == location).all()]

def create_data(db: Session, data: schemas.TemperatureValue):
    db_data = models.Data(**{"value": data.value, "location": data.location, "device_id": data.device_id, "timestamp": datetime.datetime.now() })
    db.add(db_data)
    db.commit()
    db.refresh(db_data)
    return db_data