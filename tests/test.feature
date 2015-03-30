Feature: Accident Report Email notifications 
  In order to keep track of what's going on
  As the incident manager
  I want to receive emails when a significant event occurs

  Background:
    Given I perform HTTP authentication as a "user"
    When I go to the homepage
    Then I should see "WARNING! This site is restricted"

  @active  @testing @another
  Scenario: Notification of a new Accident Report
    Given a clear email queue
    And I am on the new_accident_report page
    Then I should see "New Accident Report"
    #  When I build a "accident_report" instance from FactoryGirl
    And I create an accident report
      | field                 | value             |
      | accident_date         | 2013-01-20        |
      | accident_time         | 10:00             |
      | accident_location     | Here and there    |
      | accident_description  | I came, I saw, I hit him |
      | drivers_name          | Bilbo Baggins     |
      | drivers_license_no    | N4445555          |
    And I press "Create Accident report"
    Then I should see "Accident report was successfully created"
    But I should not see "Error"

  Scenario Outline: Send notification emails
    Given a clear email queue
    When I create an email template with <message>
    And I email <addressee>
    Then "manager@biz.com" should receive an email
    And they should see <message> in the email

    Examples:
      | addressee | message |
      | j@s.com | Finished  |
      | b@j.com | All done! |
