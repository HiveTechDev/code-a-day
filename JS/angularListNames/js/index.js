var app = angular.module('app', []);

app.controller('nameCtrl', function nameCtrl($scope) {

  $scope.names = [{
    firstName: "tyler",
    lastName: "hall"
  }];

  $scope.countNames = function() {
    return $scope.names.length;
  };
});

app.filter('capitalize', function() {
  return function(input) {
    return (!!input) ? input.charAt(0).toUpperCase() + input.substr(1).toLowerCase() : '';
  }
});