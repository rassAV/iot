from sqlalchemy import Column, Integer, String, Float, DATETIME
from database import Base

class Data(Base):
    __tablename__ = "data"
    id = Column(Integer, primary_key=True)
    value = Column(Float)
    location = Column(String)
    device_id = Column(String)
    timestamp = Column(DATETIME)