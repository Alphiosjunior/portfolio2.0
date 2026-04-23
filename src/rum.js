import { AwsRum } from 'aws-rum-web';

try {
  new AwsRum('94da366e-9438-42ba-a212-72a3b9b116c3', '1.0.0', 'eu-north-1', {
    sessionSampleRate: 1,
    identityPoolId: 'eu-north-1:7ab3b592-6b11-4dea-8881-359700f93aae',
    endpoint: 'https://dataplane.rum.eu-north-1.amazonaws.com',
    telemetries: ['performance', 'errors', 'http'],
    allowCookies: true,
    enableXRay: false,
  });
} catch (e) {}
