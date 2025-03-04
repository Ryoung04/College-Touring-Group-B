# College Campus Tour Application

A Qt-based desktop application for planning college campus visits and managing souvenir purchases.

## Features

### Trip Planning
- Select and plan visits to multiple college campuses
- Calculate total distance between selected campuses
- Optimize routes with shortest path algorithm
- Pre-defined trip options from popular starting points:
  - Saddleback College (all campuses)
  - Arizona State University (custom number)
  - UC Irvine (13 campuses)

### Souvenir Shopping
- Browse and purchase souvenirs from each campus
- Real-time cost calculation
- Persistent shopping cart

### User Management
- Secure login system
- User registration
- Admin panel for database maintenance

## Application Flow

1. **Authentication**
   - Login or register new account
   - Access main dashboard

2. **Trip Planning**
   - Select campuses from list
   - View distance calculations
   - Optional route optimization
   - Review trip summary

3. **Souvenir Selection**
   - Browse campus-specific souvenirs
   - Add items to cart
   - View total purchase cost

4. **Admin Functions**
   - Add/modify campus information
   - Manage souvenir inventory
   - Update pricing
   - Database maintenance

## Technical Details

- Built with C++ and Qt Framework
- Data stored in CSV format
- Persistent data storage
- Input validation and error handling
- Distance calculations in integer miles
- Pricing in double precision

## Database Schema

### Users Table (users.csv)
- userID (string): Primary key
- username (string): Unique
- password (string): Hashed
- isAdmin (boolean)
- dateCreated (timestamp)

### Campuses Table (campuses.csv)
- campusID (int): Primary key
- name (string)
- state (string)
- undergraduateCount (int)
- startingDate (date)
- location (string)
- distanceFromStart (int)

### Distances Table (distances.csv)
- fromCampusID (int): Foreign key
- toCampusID (int): Foreign key
- distance (int)
- Primary key: (fromCampusID, toCampusID)

### Souvenirs Table (souvenirs.csv)
- souvenirID (int): Primary key
- campusID (int): Foreign key
- name (string)
- price (double)
- quantity (int)
- category (string)

### Purchases Table (purchases.csv)
- purchaseID (int): Primary key
- userID (string): Foreign key
- timestamp (datetime)
- totalAmount (double)

### PurchaseItems Table (purchase_items.csv)
- purchaseID (int): Foreign key
- souvenirID (int): Foreign key
- quantity (int)
- priceAtPurchase (double)
- Primary key: (purchaseID, souvenirID)

## Development Roadmap

### Phase 1: Foundation (Week 1-2)
- [ ] Project setup and Qt configuration
- [ ] Database structure implementation
- [ ] Basic UI layout design
- [ ] User authentication system
- [ ] File I/O operations for CSV handling

### Phase 2: Core Features (Week 3-4)
- [ ] Campus management system
- [ ] Distance calculation implementation
- [ ] Trip planning algorithm
- [ ] Basic souvenir management
- [ ] Shopping cart functionality

### Phase 3: Advanced Features (Week 5-6)
- [ ] Route optimization algorithm
- [ ] Pre-defined trip implementations
- [ ] Advanced souvenir features
- [ ] Purchase history tracking
- [ ] Admin panel development

### Phase 4: Enhancement (Week 7-8)
- [ ] UI/UX improvements
- [ ] Performance optimization
- [ ] Error handling
- [ ] Input validation
- [ ] Testing and debugging

### Phase 5: Finalization (Week 9-10)
- [ ] Documentation
- [ ] User manual
- [ ] Final testing
- [ ] Bug fixes
- [ ] Release preparation

## Project Structure

## Data Management

The application uses CSV files to store:
- Campus information
- Inter-campus distances
- Souvenir details and pricing
- User credentials

## Security Features

- Password-protected admin access
- Input validation
- Error handling
- Secure data persistence

## Getting Started

1. Launch the application
2. Create an account or log in
3. Choose between Trip Planner or Souvenir Selector
4. Follow on-screen instructions

For admin access, contact system administrator for credentials. 