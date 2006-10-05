#! /bin/perl

package MIME::Lite::HTML;

# source-highlight associates .pl to Prolog, but this is a perl file
# this tests --infer-lang command line option, that overrides the
# standard language specification

use LWP::UserAgent;
use HTML::LinkExtor;
use URI::URL;
use MIME::Lite;
use strict;
use vars qw($VERSION @ISA @EXPORT @EXPORT_OK);

require Exporter;

@ISA = qw(Exporter);
@EXPORT = qw();

my $LOGINDETAILS;

#------------------------------------------------------------------------------
# redefine get_basic_credentials
#------------------------------------------------------------------------------
{
    package RequestAgent;
    use vars qw(@ISA);
    @ISA = qw(LWP::UserAgent);

    sub new
    { 
	my $self = LWP::UserAgent::new(@_);
	$self;
    }

    sub get_basic_credentials
	{	
	  my($self, $realm, $uri) = @_;
	  # Use parameter of MIME-Lite-HTML, key LoginDetails
	  if (defined $LOGINDETAILS) { return split(':', $LOGINDETAILS, 2); } 
	  # Ask user on STDIN
	  elsif (-t) 
	    {
		my $netloc = $uri->host_port;
		print "Enter username for $realm at $netloc: ";
		my $user = <STDIN>;
		chomp($user);
		# 403 if no user given
		return (undef, undef) unless length $user;
		print "Password: ";
		system("stty -echo");
		my $password = <STDIN>;
		system("stty echo");
		print "\n";  # because we disabled echo
		chomp($password);
		return ($user, $password);
	    }
	  # Damm we got 403 with CGI (use param LoginDetails)  ...
	  else { return (undef, undef) }
	}
  }

